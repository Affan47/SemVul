print_object(void *object)
{


	fprintf(_where, "(%s %p)", OBJECT_class(object)->name, object);


}
