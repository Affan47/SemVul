mark_as_needed_g(int code)
{
    ASSERT_GLULX();
    if (veneer_routine_needs_compilation[code] == VR_UNUSED)
    {   veneer_routine_needs_compilation[code] = VR_CALLED;


        switch(code)
        {
            case PrintShortName_VR:
                mark_as_needed_g(Metaclass_VR);
                return;
            case Print__Pname_VR:
                mark_as_needed_g(PrintShortName_VR);
                return;
            case WV__Pr_VR:
                mark_as_needed_g(RA__Pr_VR);
                mark_as_needed_g(RT__TrPS_VR);
                mark_as_needed_g(RT__Err_VR);
                return;
            case RV__Pr_VR:
                mark_as_needed_g(RA__Pr_VR);
                mark_as_needed_g(RT__Err_VR);
                return;
            case CA__Pr_VR:
                mark_as_needed_g(RA__Pr_VR);
                mark_as_needed_g(RL__Pr_VR);
                mark_as_needed_g(PrintShortName_VR);
                mark_as_needed_g(Print__Pname_VR);
                mark_as_needed_g(Z__Region_VR);
                mark_as_needed_g(Cl__Ms_VR);
                mark_as_needed_g(Glk__Wrap_VR);
                mark_as_needed_g(RT__Err_VR);
                return;
            case IB__Pr_VR:
            case IA__Pr_VR:
            case DB__Pr_VR:
            case DA__Pr_VR:
                mark_as_needed_g(RT__Err_VR);
                mark_as_needed_g(RT__TrPS_VR);
                return;
            case RA__Pr_VR:
                mark_as_needed_g(OC__Cl_VR);
                mark_as_needed_g(CP__Tab_VR);
                return;
            case RL__Pr_VR:
                mark_as_needed_g(OC__Cl_VR);
                mark_as_needed_g(CP__Tab_VR);
                return;
            case RA__Sc_VR:
                mark_as_needed_g(OC__Cl_VR);
                mark_as_needed_g(RT__Err_VR);
                return;
            case OP__Pr_VR:
                mark_as_needed_g(RA__Pr_VR);
                mark_as_needed_g(Z__Region_VR);
                return;
            case OC__Cl_VR:
                mark_as_needed_g(RA__Pr_VR);
                mark_as_needed_g(RL__Pr_VR);
                mark_as_needed_g(Z__Region_VR);
                mark_as_needed_g(RT__Err_VR);
                return;
            case Copy__Primitive_VR:
                mark_as_needed_g(CP__Tab_VR);
                return;
            case Z__Region_VR:
                mark_as_needed_g(Unsigned__Compare_VR);
                return;
            case CP__Tab_VR:
            case Metaclass_VR:
                mark_as_needed_g(Z__Region_VR);
                return;
            case Cl__Ms_VR:
                mark_as_needed_g(OC__Cl_VR);
                mark_as_needed_g(OP__Pr_VR);
                mark_as_needed_g(RT__Err_VR);
                mark_as_needed_g(Copy__Primitive_VR);
                mark_as_needed_g(OB__Remove_VR);
                mark_as_needed_g(OB__Move_VR);
                return;
            case RT__ChG_VR:
            case RT__ChGt_VR:
                mark_as_needed_g(RT__Err_VR);
                return;
            case RT__ChR_VR:
                mark_as_needed_g(RT__Err_VR);
                mark_as_needed_g(Z__Region_VR);
                mark_as_needed_g(OB__Remove_VR);
                return;
            case RT__ChT_VR:
                mark_as_needed_g(RT__Err_VR);
                mark_as_needed_g(Z__Region_VR);
                mark_as_needed_g(OB__Move_VR);
                return;
            case RT__ChPS_VR:
                mark_as_needed_g(RT__Err_VR);
                mark_as_needed_g(RT__TrPS_VR);
                mark_as_needed_g(WV__Pr_VR);
                return;
            case RT__ChPR_VR:
                mark_as_needed_g(RT__Err_VR);
                mark_as_needed_g(RV__Pr_VR); return;
            case RT__ChLDB_VR:
            case RT__ChLDW_VR:
            case RT__ChSTB_VR:
            case RT__ChSTW_VR:
                mark_as_needed_g(Unsigned__Compare_VR);
                mark_as_needed_g(RT__Err_VR);
                return;
            case RT__ChPrintC_VR:
                mark_as_needed_g(RT__Err_VR);
                return;
            case RT__ChPrintA_VR:
                mark_as_needed_g(Unsigned__Compare_VR);
                mark_as_needed_g(RT__Err_VR);
                mark_as_needed_g(Print__Addr_VR);
                return;
            case RT__ChPrintS_VR:
            case RT__ChPrintO_VR:
                mark_as_needed_g(RT__Err_VR);
                mark_as_needed_g(Z__Region_VR);
                return;
            case Print__Addr_VR:
                mark_as_needed_g(RT__Err_VR);
                return;
            case Dynam__String_VR:
                mark_as_needed_g(RT__Err_VR);
                return;
        }
    }
}
