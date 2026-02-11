DestroyFixture(b2Fixture* fixture)
{
	b2Assert(m_world->IsLocked() == false);
	if (m_world->IsLocked() == true)
	{
		return;
	}

	b2Assert(fixture->m_body == this);


	b2Assert(m_fixtureCount > 0);
	b2Fixture** node = &m_fixtureList;
	bool found = false;
	while (*node != NULL)
	{
		if (*node == fixture)
		{
			*node = fixture->m_next;
			found = true;
			break;
		}

		node = &(*node)->m_next;
	}


	b2Assert(found);


	b2ContactEdge* edge = m_contactList;
	while (edge)
	{
		b2Contact* c = edge->contact;
		edge = edge->next;

		b2Fixture* fixtureA = c->GetFixtureA();
		b2Fixture* fixtureB = c->GetFixtureB();

		if (fixture == fixtureA || fixture == fixtureB)
		{


			m_world->m_contactManager.Destroy(c);
		}
	}

	b2BlockAllocator* allocator = &m_world->m_blockAllocator;

	if (m_flags & e_activeFlag)
	{
		b2BroadPhase* broadPhase = &m_world->m_contactManager.m_broadPhase;
		fixture->DestroyProxies(broadPhase);
	}

	fixture->Destroy(allocator);
	fixture->m_body = NULL;
	fixture->m_next = NULL;
	fixture->~b2Fixture();
	allocator->Free(fixture, sizeof(b2Fixture));

	--m_fixtureCount;


	ResetMassData();
}
