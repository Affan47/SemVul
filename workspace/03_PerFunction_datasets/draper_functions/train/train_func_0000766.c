setShellRadii(real *rshell) const
{
    static const real facl[] = {
        1.0, 1.33, 1.6, 1.83, 2.03, 2.22, 2.39, 2.55, 2.70, 2.84 };
    real thlog = std::log(SET_SHELL_RADII_ORBITAL_THR);
    int ishela, iprim;

    for(ishela=0; ishela <bis.noOfShells; ishela++) {
        const ShellSpecStruct& currShell = bis.shellList[ishela];
        rshell[ishela] =  0.0;
        for(iprim=0; iprim<currShell.noOfContr; iprim++) {
            ergo_real absCoeff = std::fabs(currShell.coeffList[iprim]);
            if(absCoeff>0) {
              real r2 = (std::log(absCoeff)-thlog)/
                    currShell.exponentList[iprim];
                if(rshell[ishela]<r2) rshell[ishela] = r2;
            }
        }
    }
    for(ishela=0; ishela <bis.noOfShells; ishela++) {
        rshell[ishela] = std::sqrt(rshell[ishela])
            *facl[bis.shellList[ishela].shellType];
    }
}
