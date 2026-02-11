IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Generator") {
        if (tag->hasChildren())
            setGenerator(plParticleGenerator::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "EmitterParams") {
        fSpanIndex = tag->getParam("SpanIndex", "0").toUint();
        fMaxParticles = tag->getParam("MaxParticles", "0").toUint();
        fMiscFlags = tag->getParam("MiscFlags", "0").toUint();
    } else if (tag->getName() == "Color") {
        if (tag->hasChildren())
            fColor.prcParse(tag->getFirstChild());
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
