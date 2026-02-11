getBlockAnnotationValue (Annotation *ann, Tag *tag, std::string func) {

    Annotation::ActualMap::iterator actual = ann->actuals.find (func);
    if (actual == ann->actuals.end()) {

        Interface *iface = ann->iface;
        InterpretedBlock *block = (InterpretedBlock*)tag->block;
        if (block->parameters.size() != 0) {

            return block->parameters[0]->def;
        }
        return NULL;
    } else {
        return actual->second;
    }
}
