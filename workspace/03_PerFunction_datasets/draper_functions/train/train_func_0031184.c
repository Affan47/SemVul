operator=(HtVector &vector)
{
    Destroy();

    for(int i = 0; i < vector.Count(); i++)
      Add(vector.data[i]->Copy());

    return *this;
}
