SetTexCoords(int num,BindType bind,const float64 *data)
{
    if (num < 0)
        return;

    trpgTexData td;
    td.set(num,bind,data);
    texData.push_back(td);
}
