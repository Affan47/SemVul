HtmlComputedValuesFreePrototype(pTree)
    HtmlTree *pTree;
{
    if (pTree->pPrototypeCreator) {
        pTree->pPrototypeCreator->values.nRef = 1;
        HtmlComputedValuesRelease(pTree, &pTree->pPrototypeCreator->values);
        HtmlFree(pTree->pPrototypeCreator);
        pTree->pPrototypeCreator = 0;
    }
}
