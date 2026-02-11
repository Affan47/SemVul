recalculate(CdlTransaction transaction)
{
    CYG_REPORT_FUNCNAME("CdlInterface::recalculate");

    const CdlValue& old_value = transaction->get_whole_value(this);

    cdl_int count = 0;
    std::vector<CdlValuable> implementers;
    std::vector<CdlValuable>::const_iterator valuable_i;
    this->get_implementers(implementers);
    for (valuable_i = implementers.begin(); valuable_i != implementers.end(); valuable_i++) {
        if (transaction->is_active(*valuable_i)) {
            const CdlValue& implementer_value = transaction->get_whole_value(*valuable_i);
            if (implementer_value.is_enabled()) {
                count++;
            }
        }
    }


    switch(this->get_flavor()) {
      case CdlValueFlavor_Bool :
        {
            bool new_bool = (count > 0);
            if (new_bool != old_value.is_enabled()) {
                CdlValue new_value = old_value;
                new_value.set_enabled(new_bool, CdlValueSource_Default);
                transaction->set_whole_value(this, old_value, new_value);
            }
            break;
        }
      case CdlValueFlavor_BoolData:
        {


            if (count != old_value.get_integer_value()) {
                CdlValue new_value = old_value;
                new_value.set_enabled_and_value(count > 0, count, CdlValueSource_Default);
                transaction->set_whole_value(this, old_value, new_value);
            }

            break;
        }
      case CdlValueFlavor_Data:
        {
            if (count != old_value.get_integer_value()) {
                CdlValue new_value = old_value;
                new_value.set_integer_value(count, CdlValueSource_Default);
                transaction->set_whole_value(this, old_value, new_value);
            }
            break;
        }

      default:
        break;
    }

    CYG_REPORT_RETURN();
}
