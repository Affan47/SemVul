getPPDefines(Perm permutation)
        {
            String strPPD;


            String lightType;
            if (permutation & LightMaterialGenerator::MI_POINT)
            {
                lightType = "POINT";
            }
            else if (permutation & LightMaterialGenerator::MI_SPOTLIGHT)
            {
                lightType = "SPOT";
            }
            else if (permutation & LightMaterialGenerator::MI_DIRECTIONAL)
            {
                lightType = "DIRECTIONAL";
            }
            else
            {
                assert(false && "Permutation must have a light type");
            }
            strPPD += "-DLIGHT_TYPE=LIGHT_" + lightType + " ";


            if (permutation & LightMaterialGenerator::MI_SPECULAR)
            {
                strPPD += "-DIS_SPECULAR ";
            }
            if (permutation & LightMaterialGenerator::MI_ATTENUATED)
            {
                strPPD += "-DIS_ATTENUATED ";
            }
            if (permutation & LightMaterialGenerator::MI_SHADOW_CASTER)
            {
                strPPD += "-DIS_SHADOW_CASTER ";
            }
            return strPPD;
        }
