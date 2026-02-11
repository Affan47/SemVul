cmd_add (const std::vector<std::string> cdl_packages)
{
    bool status = false;
    try {
        init(true);
        for (unsigned int n = 0; n < cdl_packages.size (); n++) {
            config->load_package (resolve_package_alias (cdl_packages [n]), "", &diagnostic_handler, &diagnostic_handler);
        }
        if (debug_level_set) {
            this->update_debug_level();
        }
        if (!no_resolve) {
            CdlTransactionBody::set_callback_fn(&transaction_callback);
            config->resolve_all_conflicts();
        }
        report_conflicts();
        if (!no_updates) {
            config->save (savefile);
        }
        if (ignore_errors || (0 == config->get_all_conflicts().size())) {
            status = true;
        }
    } catch (CdlStringException exception) {
        exception_handler (exception);
    } catch (...) {
        exception_handler ();
    }

    delete_cdl_data ();
    return status;
}
