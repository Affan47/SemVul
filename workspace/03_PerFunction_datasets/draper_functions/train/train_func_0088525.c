text()
{
    TextElement* t = new TextElement();
    elements.push_back( t );
    indentation = false;
    return *t;
}
