GeomPosition(Geom *object, Transform T)
{
    if( object && object->Class->position )
	(*object->Class->position)(object, T);
    else if (T)
	TmIdentity(T);
    return object;
}
