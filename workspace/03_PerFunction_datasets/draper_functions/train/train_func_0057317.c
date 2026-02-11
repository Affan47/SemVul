AddContactToNode(const CONTACT_KEY * contactkey,CONTACT_KEY_HASH_NODE * node)
{
	for(int i=0;i<node->m_keycount;i++)
	{
		if(node->m_keyarray[i].m_key == contactkey->m_key)
		{
			dContactGeom *contactfound = node->m_keyarray[i].m_contact;
			if (dDISTANCE(contactfound->pos, contactkey->m_contact->pos) < REAL(1.00001)  * dSQRT3 / CONTACT_POS_HASH_QUOTIENT )
			{
				return contactfound;
			}
		}
	}

	if (node->m_keycount < MAXCONTACT_X_NODE)
	{
		node->m_keyarray[node->m_keycount].m_contact = contactkey->m_contact;
		node->m_keyarray[node->m_keycount].m_key = contactkey->m_key;
		node->m_keycount++;
	}
	else
	{
		dDEBUGMSG("Trimesh-trimesh contach hash table bucket overflow - close contacts might not be culled");
	}

	return contactkey->m_contact;
}
