operator<<(std::ostream& os, CItem& c)
{
    os << "CItem " << c.getName() << std::endl;

    os << "  base: ";
    for (int i = 0; i < kNumMods; i++) {
        os << c.getBaseStat(static_cast<ModifierType>(i)) << ", ";
    }

    os << std::endl << "  modified: ";
    for (int i = 0; i < kNumMods; i++) {
        os << c.getStat(static_cast<ModifierType>(i)) << ", ";
    }

    return os;
}
