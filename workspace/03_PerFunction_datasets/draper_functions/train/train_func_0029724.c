validate(const char *pString_)
{ return (MSView::model()!=0)?((value().set(pString_)==MSError::MSSuccess)?MSTrue:MSFalse):MSTrue; }
