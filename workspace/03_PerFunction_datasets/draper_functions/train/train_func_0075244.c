lookup(struct in_addr ia)


{
	register char * name;

	if(flags.lookup == 0)
		return inet_ntoa(ia);


	name = (char *)_l_get(ia);

	return ( (name == NULL)
		 ? (char *)lookup_new(ia)
		 : (char *)name );
}
