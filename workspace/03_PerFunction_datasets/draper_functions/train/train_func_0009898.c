SubstituteWithBlackIfNeeded(const void*& data)
    {


        static bool Deviate = false;
        static short* Replacement = 0;
        static unsigned wid=0, hei=0;
        if(Deviate)
        {
            if(Replacement) { delete[] Replacement; Replacement=0; }
            return;
        }

        unsigned dim = LogoInfo::width * LogoInfo::height;
        const short* p = (const short*)data;
        for(unsigned a=0; a<dim; ++a)
            if(p[a] != p[0])
            {
                Deviate = true;
                return;
            }

        if(Replacement && (wid != LogoInfo::width || hei != LogoInfo::height))
        {
            delete[] Replacement;
            Replacement = 0;
        }

        wid = LogoInfo::width;
        hei = LogoInfo::height;

        if(!Replacement)
        {
            Replacement = new short[dim];
            for(unsigned a=0; a<dim; ++a) Replacement[a]=0x0000;
        }
        data = (void*)Replacement;
    }
