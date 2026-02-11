coerce_to_package(p)
object p;
{
	object pp;

	if (type_of(p) == t_package)
		return(p);
	pp = find_package(p);
	if (pp == Cnil)
		no_package(p);
	return(pp);
}
