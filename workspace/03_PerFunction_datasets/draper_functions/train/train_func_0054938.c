test_vdelete(void)
{
    int32 fid;
    int32 vgroup_id;
    int32 status;
    int32 vg_ref;


    fid = Hopen(FNAME0, DFACC_RDWR, 0);
    CHECK_VOID(fid,FAIL,"Hopen:tvset.hdf");


    status = Vstart(fid);
    CHECK_VOID(status,FAIL,"Vstart:fid");


    vgroup_id = Vattach(fid, -1, "w");
    CHECK_VOID(vgroup_id,FAIL,"Vattach:vgroup_id");


    status = Vsetname(vgroup_id, "Vgroup should have been deleted");
    CHECK_VOID(status,FAIL,"Vsetname:vgroup_id");

    status = Vsetclass(vgroup_id, "Vgroup should have been deleted");
    CHECK_VOID(status,FAIL,"Vsetclass:vgroup_id");


    vg_ref = VQueryref(vgroup_id);
    CHECK_VOID(vg_ref,FAIL,"VQueryref:vgroup_id");


    status = Vdetach(vgroup_id);
    CHECK_VOID(status,FAIL,"Vdetach:vgroup_id");


    status = Vend(fid);
    CHECK_VOID(status,FAIL,"Vend:fid");

    status = Hclose(fid);
    CHECK_VOID(status,FAIL,"Hclose:fid");


    fid = Hopen(FNAME0, DFACC_RDWR, 0);
    CHECK_VOID(fid,FAIL,"Hopen:tvset.hdf");


    status = Vstart(fid);
    CHECK_VOID(status,FAIL,"Vstart:fid");


    vgroup_id = Vattach(fid, vg_ref, "w");
    CHECK_VOID(vgroup_id,FAIL,"Vattach:vgroup_id");


    status = Vdelete(fid, vg_ref);
    CHECK_VOID(status,FAIL,"Vdelete:vgroup_id");


    status = Vdetach(vgroup_id);
    CHECK_VOID(status,FAIL,"VSdetach:vgroup_id");


    status = Vend(fid);
    CHECK_VOID(status,FAIL,"Vend:fid");

    status = Hclose(fid);
    CHECK_VOID(status,FAIL,"Hclose:fid");


    fid = Hopen(FNAME0, DFACC_RDONLY, 0);
    CHECK_VOID(fid,FAIL,"Hopen:tvset.hdf");


    status = Vstart(fid);
    CHECK_VOID(status,FAIL,"Vstart:fid");


    vgroup_id = Vattach(fid, vg_ref, "w");
    if(vgroup_id != FAIL)
      {
          num_errs++;
          printf(">>> Vdelete failed to delete vdata \n");
      }


    status = Vend(fid);
    CHECK_VOID(status,FAIL,"Vend:fid");

    status = Hclose(fid);
    CHECK_VOID(status,FAIL,"Hclose:fid");

}
