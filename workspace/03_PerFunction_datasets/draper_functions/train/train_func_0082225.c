Eval5InputsFloat(const cmsFloat32Number Input[],
                      cmsFloat32Number Output[],
                      const cmsInterpParams* p)
{
       const cmsFloat32Number* LutTable = (cmsFloat32Number*) p -> Table;
       cmsFloat32Number rest;
       cmsFloat32Number pk;
       int k0, K0, K1;
       const cmsFloat32Number* T;
       cmsUInt32Number i;
       cmsFloat32Number Tmp1[MAX_STAGE_CHANNELS], Tmp2[MAX_STAGE_CHANNELS];
       cmsInterpParams p1;

       pk = Input[0] * p->Domain[0];
       k0 = _cmsQuickFloor(pk);
       rest = pk - (cmsFloat32Number) k0;

       K0 = p -> opta[4] * k0;
       K1 = K0 + (Input[0] >= 1.0 ? 0 : p->opta[4]);

       p1 = *p;
       memmove(&p1.Domain[0], &p ->Domain[1], 4*sizeof(cmsUInt32Number));

       T = LutTable + K0;
       p1.Table = T;

       Eval4InputsFloat(Input + 1,  Tmp1, &p1);

       T = LutTable + K1;
       p1.Table = T;

       Eval4InputsFloat(Input + 1,  Tmp2, &p1);

       for (i=0; i < p -> nOutputs; i++) {

              cmsFloat32Number y0 = Tmp1[i];
              cmsFloat32Number y1 = Tmp2[i];

              Output[i] = y0 + (y1 - y0) * rest;
       }
}
