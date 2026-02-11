printMatch(const std::string& s1, const std::string& s2) const
{
    std::string matched1 = coord[0].getSubstring(s1);
    std::string matched2 = coord[1].getSubstring(s2);

    if(isReverse)
        matched2 = reverseComplement(matched2);

    std::cout << "M1: " << matched1 << "\n";
    std::cout << "M2: " << matched2 << "\n";
}
