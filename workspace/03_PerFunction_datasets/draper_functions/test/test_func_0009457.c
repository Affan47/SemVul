createMovie(Global_as& gl, DisplayObject* parent)
{
    as_object* o = getObjectWithPrototype(gl, NSV::CLASS_MOVIE_CLIP);
    return new SWFMovie(o, this, parent);
}
