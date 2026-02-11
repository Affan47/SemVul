get(const plString& name) {
    for (size_t i=0; i<fVariables.getSize(); i++)
        if (fVariables[i]->getName() == name)
            return fVariables[i];
    return NULL;
}
