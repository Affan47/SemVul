readINITree(std::istream& in,
                                            ParameterTree& pt,
                                            bool overwrite)
{
    readINITree(in, pt, "stream", overwrite);
}
