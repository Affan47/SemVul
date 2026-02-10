print()
{
    std::ostringstream os;
    os<<"\n";
    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            os << m[i][j] <<" ";
        }
        os << "\n";
    }
    return os.str();
}
