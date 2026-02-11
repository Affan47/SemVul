update(CdlTransaction transact, CdlNode source, CdlNode dest, CdlUpdate change)
{
    CYG_REPORT_FUNCNAME("CdlProperty_Reference::update");
    CYG_REPORT_FUNCARG5XV(this, transact, source, dest, change);
    CYG_PRECONDITION_THISC();

    switch(change) {

      case CdlUpdate_Loaded :
      {


        CYG_ASSERTC(0 == dest);
        CdlToplevel toplevel = source->get_toplevel();
        std::string dest_name = get_destination_name();
        if ("" != dest_name) {
            dest = toplevel->lookup(dest_name);
            if (0 == dest) {
                CdlConflict_UnresolvedBody::make(transact, source, this, get_destination_name());
            } else {
                bind(source, this, dest);
            }
        }
        break;
      }

      case CdlUpdate_Unloading:
      {


        CYG_ASSERTC(0 == dest);
        dest = get_destination();
        if (0 != dest) {
            unbind(source, this);
        }
        break;
      }

      case CdlUpdate_Created:
      {


        CYG_ASSERT_CLASSC(dest);

        bind(source, this, dest);

        CdlConflict conflict = transact->get_structural_conflict(source, this, &CdlConflict_UnresolvedBody::test);
        CYG_ASSERTC(0 != conflict);
        transact->clear_conflict(conflict);
        break;
      }
      case CdlUpdate_Destroyed :
      {


        CYG_ASSERT_CLASSC(dest);
        unbind(source, this);
        CdlConflict_UnresolvedBody::make(transact, source, this, get_destination_name());
        break;
      }


      default:
        break;
    }

    (*update_handler)(transact, source, this, dest, change);

    CYG_REPORT_RETURN();
}
