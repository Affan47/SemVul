testUniqueNames(vector<Sequence>* seqVector, string *offendingSeq)
{
    vector<string>::iterator   oldName;
    vector<Sequence>::iterator newName;
    bool unique = true;


    for (newName = seqVector->begin(); unique && newName != seqVector->end(); newName++) {

        for (oldName = names.begin() + 1; unique && oldName != names.end(); oldName++) {
            if (*oldName == newName->getName()) {
                offendingSeq->assign(*oldName);
                unique = false;
            }
        }
    }
    return unique;
}
