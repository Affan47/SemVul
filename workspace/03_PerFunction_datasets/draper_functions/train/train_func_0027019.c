print(ostream& out)
{
    this->printBefore(out);
    for (int i=0; i<mChildren.size(); ++i)
    {
        mChildren[i]->print(out);
    }
    this->printAfter(out);
}
