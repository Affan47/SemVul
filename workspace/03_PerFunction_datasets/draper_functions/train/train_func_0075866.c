PrintConcept ( std::ostream& o, const TConcept* p ) const
{

	if ( isValid(p->pName) )
	{
		o << getCTTagName(p->getClassTag());

		if ( p->isSingleton() )
			o << (p->isNominal() ? 'o' : '!');

		o << '.' << p->getName() << " [" << p->tsDepth
		  << "] " << (p->isNonPrimitive() ? "=" : "[=");

		if ( isValid (p->pBody) )
			PrintDagEntry ( o, p->pBody );


		if ( p->Description != NULL )
			o << (p->isNonPrimitive() ? "\n-=" : "\n-[=") << p->Description;

		o << "\n";
	}
}
