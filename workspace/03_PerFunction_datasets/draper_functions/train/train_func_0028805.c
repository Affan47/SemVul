random(int letters)
{
    static bool seeded = false;
    if (!seeded) {
        unsigned long long randomSeed = (unsigned long long)time(0);
#ifdef WIN32
        HMODULE hLib = LoadLibrary(TEXT("ADVAPI32.DLL"));
        if (hLib) {
            BOOLEAN (APIENTRY *pfn)(void*, ULONG) =
                (BOOLEAN (APIENTRY *)(void*, ULONG))GetProcAddress(hLib, "SystemFunction036");
            if (pfn)
                pfn(&randomSeed, (ULONG)sizeof(randomSeed));

            FreeLibrary(hLib);
        }
#else

        std::ifstream urand("/dev/urandom", std::ios::in | std::ios::binary);
        if (urand.is_open()) {
            urand.read((char*)(&randomSeed), sizeof(randomSeed));
            urand.close();
        }
#endif
        Rand64::Common.seed(randomSeed);
        seeded = true;
    }

    int min = recommendedMin();
    int max = recommendedMax(letters);
    for (;;) {
        unsigned long rnd = Rand64::Common.getUnsigned();
        if (rnd + max > rnd)
            return min + rnd % (max - min + 1);
    }
}
