Hokuyo_UTM()
{
	CSetOfObjectsPtr ret = CSetOfObjects::Create();

	{
		CBoxPtr base = CBox::Create(TPoint3D(-0.03,-0.03,-0.055),TPoint3D(0.03,0.03,-0.014));
		base->setColor(0,0,0);
		ret->insert(base);
	}
	{
		CCylinderPtr cyl1 = CCylinder::Create(0.028,0.024,0.028);
		cyl1->setColor(0,0,0);
		cyl1->setPose(CPose3D(0,0,-0.014));
		ret->insert(cyl1);
	}
	{
		CCylinderPtr cyl2 = CCylinder::Create(0.028,0.028,0.01);
		cyl2->setColor(1,69/255.0,0);
		cyl2->setPose(CPoint3D(0,0,0.014));
		ret->insert(cyl2);
	}
	{
		CCylinderPtr cyl3 = CCylinder::Create(0.028,0.028,0.01);
		cyl3->setColor(0,0,0);
		cyl3->setPose(CPoint3D(0,0,0.024));
		ret->insert(cyl3);
	}

    return ret;
}
