reportStatus(std::size_t fileindex, std::size_t filecount, std::size_t sizedone, std::size_t sizetotal)
{
    if (filecount > 1) {
        std::ostringstream oss;
        oss << fileindex << '/' << filecount
            << " files checked " <<
            (sizetotal > 0 ? static_cast<long>(static_cast<long double>(sizedone) / sizetotal*100) : 0)
            << "% done";
        std::cout << oss.str() << std::endl;
    }
}
