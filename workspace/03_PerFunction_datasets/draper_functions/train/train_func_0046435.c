init(string s, int stage, string *regname=NULL)
        {
            arg = s;
            comp = GL_RGB;
            alphaComp = GL_ALPHA;
            map = GL_SIGNED_IDENTITY_NV;

            string::size_type offset;
            if(
                (offset = s.find(".a")) != string::npos ||
                (offset = s.find(".w")) != string::npos
              )
            {
                comp = GL_ALPHA;
                s.erase(offset, offset+2);
            }
            else if ((offset = s.find(".b")) != string::npos ||
                     (offset = s.find(".z")) != string::npos)
            {
                alphaComp = GL_BLUE;
                s.erase(offset,offset+2);
            }

            bool negate = false;

            if(s[0] == '1')
            {
                s.erase(0, 1);
                while(s[0] == ' ')
                    s.erase(0,1);
                if(s[0] == '-')
                    s.erase(0,1);
                while(s[0] == ' ')
                    s.erase(0,1);
                map = GL_UNSIGNED_INVERT_NV;
            }
            else if(s[0] == '-')
            {
                s.erase(0, 1);
                while(s[0] == ' ')
                    s.erase(0,1);
                negate = true;
                map = GL_UNSIGNED_INVERT_NV;
            }

            bool half_bias = false;
            bool expand = false;
            if(s.find("_bias") != string::npos)
            {
                s.erase(s.find("_bias"), 5);
                half_bias = true;
            }
            else if(s.find("_bx2") != string::npos)
            {
                s.erase(s.find("_bx2"), 4);
                expand = true;
            }

            if(expand)
            {
                if(negate)
                    map = GL_EXPAND_NEGATE_NV;
                else
                    map = GL_EXPAND_NORMAL_NV;
            }
            else if(half_bias)
            {
                if(negate)
                    map = GL_HALF_BIAS_NEGATE_NV;
                else
                    map = GL_HALF_BIAS_NORMAL_NV;
            }
            reg = reg_enum(s,stage);

            if (regname != NULL)
                *regname = s;


            std::set<const char*, ltstr>::iterator iter =
                ps10::alphaBlueRegisters.find(s.c_str());
            if (iter != ps10::alphaBlueRegisters.end())
                alphaComp = GL_BLUE;

        }
