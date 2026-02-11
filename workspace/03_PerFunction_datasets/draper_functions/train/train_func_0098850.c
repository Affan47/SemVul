operator=(mypoint &p)
{
    if (this == &p)
        return *this ;
    x_ = p.x();
    y_ = p.y();
    z_ = p.z();
    Rval_ = p.Rval();
    Gval_ = p.Gval();
    Bval_ = p.Bval();
    nbraw_ = p.nbraw();
    radius_ = p.radius();
    hasAnnotation_ = p.hasAnnotation();
    annotation_ = p.annotation();
    stringColour_ = p.stringColour();
    stringFont_ = p.stringFont();
    stringSize_ = p.stringSize();
    stringQuadrant_ = p.stringQuadrant();
    linelength_ = p.linelength();
    selected_ = p.selected();
    hidden_ = p.isHidden();


    return *this;
}
