isStoned(const Cube *model) const
{
    int index = model->getIndex();
    if (index > -1) {
        return m_stoned[index];
    }
    else {
        return true;
    }
}
