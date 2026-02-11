init_exp(){
    int i=0;
    expvec[i++]=Vec3(0,0,1);
    expvec[i++]=Vec3(0,1,1);
    expvec[i++]=Vec3(0,-1,1);
    expvec[i++]=Vec3(1,0,1);
    expvec[i++]=Vec3(-1,0,1);
    expvec[i++]=Vec3(1,1,1);
    expvec[i++]=Vec3(-1,1,1);
    expvec[i++]=Vec3(1,-1,1);
    expvec[i++]=Vec3(-1,-1,1);

    const REAL fak=7;

    tRandomizer & randomizer = tRandomizer::GetInstance();

    for (int j=i;j<40;j++){
        expvec[i++]=Vec3(fak*( randomizer.Get() -.5f ),
                         fak*( randomizer.Get() -.5f ),
                         1);


    }

    for (int k=expvec.Len()-1;k>=0;k--)
        expvec[k]=expvec[k]*(1/expvec[k].Norm());
}
