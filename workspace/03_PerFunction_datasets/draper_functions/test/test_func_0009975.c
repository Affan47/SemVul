function_doc_signatures( function const * f)
    {
        list signatures;
        std::vector<function const*> funcs = flatten( f);
        std::vector<function const*> split_funcs = split_seq_overloads( funcs, true);
        std::vector<function const*>::const_iterator sfi=split_funcs.begin(), fi;
        size_t n_overloads=0;
        for (fi=funcs.begin(); fi!=funcs.end(); ++fi)
        {
            if(*sfi == *fi){
                if((*fi)->doc())
                {
                    str func_doc = str((*fi)->doc());

                    int doc_len = len(func_doc);

                    bool show_py_signature = doc_len >= int(sizeof(detail::py_signature_tag)/sizeof(char)-1)
                                            && str(detail::py_signature_tag) == func_doc.slice(0, int(sizeof(detail::py_signature_tag)/sizeof(char))-1);
                    if(show_py_signature)
                    {
                        func_doc = str(func_doc.slice(int(sizeof(detail::py_signature_tag)/sizeof(char))-1, _));
                        doc_len = len(func_doc);
                    }

                    bool show_cpp_signature = doc_len >= int(sizeof(detail::cpp_signature_tag)/sizeof(char)-1)
                                            && str(detail::cpp_signature_tag) == func_doc.slice( 1-int(sizeof(detail::cpp_signature_tag)/sizeof(char)), _);

                    if(show_cpp_signature)
                    {
                        func_doc = str(func_doc.slice(_, 1-int(sizeof(detail::cpp_signature_tag)/sizeof(char))));
                        doc_len = len(func_doc);
                    }

                    str res="\n";
                    str pad = "\n";

                    if(show_py_signature)
                    {
                        str sig = pretty_signature(*fi, n_overloads,false);
                        res+=sig;
                        if(doc_len || show_cpp_signature )res+=" :";
                        pad+= str("    ");
                    }

                    if(doc_len)
                    {
                        if(show_py_signature)
                            res+=pad;
                         res+= pad.join(func_doc.split("\n"));
                    }

                    if( show_cpp_signature)
                    {
                        if(len(res)>1)
                            res+="\n"+pad;
                        res+=detail::cpp_signature_tag+pad+"    "+pretty_signature(*fi, n_overloads,true);
                    }

                    signatures.append(res);
                }
                ++sfi;
                n_overloads = 0;
            }else
                ++n_overloads ;
        }

        return signatures;
    }
