ExecuteAndGetOutputAndError(const wxString& command, bool prepend_error = true)
        {
            if (!SecurityAllows(_T("Execute"), command))
                return wxEmptyString;

            wxArrayString output;
            wxArrayString error;
            wxExecute(command, output, error, wxEXEC_NODISABLE);

            wxString str_out;

            if ( prepend_error && !error.IsEmpty())
                str_out += GetStringFromArray(error,  _T("\n"));

            if (!output.IsEmpty())
                str_out += GetStringFromArray(output, _T("\n"));

            if (!prepend_error && !error.IsEmpty())
                str_out += GetStringFromArray(error,  _T("\n"));

            return  str_out;
        }
