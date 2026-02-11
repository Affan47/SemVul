display(Renderer& renderer, const Transform& base)
{
    const DisplayObject::MaskRenderer mr(renderer, *this);

    const Transform xform = base * transform();

    DisplayObjects actChars;
    getActiveCharacters(actChars);


    std::sort(actChars.begin(), actChars.end(), charDepthLessThen);

    for (DisplayObjects::iterator it = actChars.begin(), e = actChars.end();
            it != e; ++it) {
        (*it)->display(renderer, xform);
    }

    clear_invalidated();
}
