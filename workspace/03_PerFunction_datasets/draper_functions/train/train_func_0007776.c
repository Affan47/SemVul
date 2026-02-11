mysql_qetData(const fn_call& fn)
{


    if (fn.nargs > 0) {


	    as_object* arr = toObject(fn.arg(1), getVM(fn));

        MySQL::query_t qresult;

        for (size_t i=0; i<qresult.size(); i++) {
            std::vector<const char *> row;
            row = qresult[i];
            for (size_t j=0; j< row.size(); j++) {
                as_value entry = row[j];
                callMethod(arr, NSV::PROP_PUSH, entry);
            }
        }
        return as_value(true);
    }
    log_aserror("Mysql.getData(): missing arguments");
 	return as_value(false);
}
