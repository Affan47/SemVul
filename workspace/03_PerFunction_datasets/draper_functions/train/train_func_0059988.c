restore ( void )
	{
		CWDArray::iterator p = label.Base.begin() + offset;
		*p = ConceptWDep(p->bp(),dep);
	}
}
