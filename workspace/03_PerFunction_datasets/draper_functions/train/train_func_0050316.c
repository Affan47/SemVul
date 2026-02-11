generate_multiset_limit5(char *var, char * name2, int size2, int left2, bool isunion)
{
  if (isunion)
    fprintf(codefile,
	    "\n"
	    "      // refinement -- graph structure for two scalarsets\n"
	    "      //               as in array S1 of S2\n"
	    "      // only if there is more than 1 permutation in class\n"
	    "      if ( (count_multisetindex<current_size)\n"
	    "           || ( Perm.MTO_class_%s() && count_%s<%d) )\n"
	    "        {\n"
	    "          exists = FALSE;\n"
	    "          split = FALSE;\n"
	    "          for (k=0; k<current_size; k++) // step through class\n"
	    "            if ((!(*this)[k]%s.isundefined())\n"
	    "                && (*this)[k]%s>=%d\n"
	    "                && (*this)[k]%s<=%d)\n"
	    "              split = TRUE;\n"
	    "          if (split)\n"
	    "            {\n"
	    "              for (i=0; i<count_multisetindex; i++) // scan through array index priority\n"
	    "                for (j=0; j<count_%s; j++) //scan through element priority\n"
	    "                  {\n"
	    "                    exists = FALSE;\n"
	    "                    for (k=0; k<current_size; k++) // initialize goodset\n"
	    "                      goodset_multisetindex[k] = FALSE;\n"
	    "                    for (k=0; k<%d; k++) // initialize goodset\n"
	    "                      goodset_%s[k] = FALSE;\n"
	    "                    for (k=0; k<current_size; k++) // scan array index\n"
	    "                      // set goodsets\n"
	    "                      if (pos_multisetindex[i][k] \n"
	    "                          && !(*this)[k]%s.isundefined()\n"
	    "                          && (*this)[k]%s>=%d\n"
	    "                          && (*this)[k]%s<=%d\n"
	    "                          && pos_%s[j][(*this)[k]%s-%d])\n"
	    "                        {\n"
	    "                          exists = TRUE;\n"
	    "                          goodset_multisetindex[k] = TRUE;\n"
	    "                          goodset_%s[(*this)[k]%s-%d] = TRUE;\n"
	    "                        }\n"
	    "                    if (exists)\n"
	    "                      {\n"
	    "                        // set split for the array index type\n"
	    "                        split=FALSE;\n"
	    "                        for (k=0; k<current_size; k++)\n"
	    "                          if ( pos_multisetindex[i][k] && !goodset_multisetindex[k] )\n"
	    "                            split= TRUE;\n"
	    "                        if (split)\n"
	    "                          {\n"
	    "                            // move following pos entries down 1 step\n"
	    "                            for (z=count_multisetindex; z>i; z--)\n"
	    "                              for (k=0; k<current_size; k++)\n"
	    "                                pos_multisetindex[z][k] = pos_multisetindex[z-1][k];\n"
	    "                            // split pos\n"
	    "                            for (k=0; k<current_size; k++)\n"
	    "                              {\n"
	    "                                if (pos_multisetindex[i][k] && !goodset_multisetindex[k])\n"
	    "                                  pos_multisetindex[i][k] = FALSE;\n"
	    "                                if (pos_multisetindex[i+1][k] && goodset_multisetindex[k])\n"
	    "                                  pos_multisetindex[i+1][k] = FALSE;\n"
	    "                              }\n"
	    "                            count_multisetindex++;\n"
	    "                          }\n"
	    "                        // set split for the element type\n"
	    "                        split=FALSE;\n"
	    "                        for (k=0; k<%d; k++)\n"
	    "                          if ( pos_%s[j][k] && !goodset_%s[k] )\n"
	    "                            split= TRUE;\n"
	    "                        if (split)\n"
	    "                          {\n"
	    "                            // move following pos entries down 1 step\n"
	    "                            for (z=count_%s; z>j; z--)\n"
	    "                              for (k=0; k<%d; k++)\n"
	    "                                pos_%s[z][k] = pos_%s[z-1][k];\n"
	    "                            // split pos\n"
	    "                            for (k=0; k<%d; k++)\n"
	    "                              {\n"
	    "                                if (pos_%s[j][k] && !goodset_%s[k])\n"
	    "                                  pos_%s[j][k] = FALSE;\n"
	    "                                if (pos_%s[j+1][k] && goodset_%s[k])\n"
	    "                                  pos_%s[j+1][k] = FALSE;\n"
	    "                              }\n"
	    "                            count_%s++;\n"
	    "                          }\n"
	    "                      }\n"
	    "                  }\n"
	    "            }\n"
	    "        }\n",
	    name2, name2, size2,
	    var,
	    var, left2,
	    var, left2+size2-1,

	    name2,
	    size2, name2,

	    var,
	    var, left2,
	    var, left2+size2-1,
	    name2, var, left2,
	    name2, var, left2,

	    size2,
	    name2, name2,
	    name2, size2, name2, name2,
	    size2, name2, name2, name2,
	    name2, name2, name2,
	    name2

	    );
  else
    fprintf(codefile,
	    "\n"
	    "      // refinement -- graph structure for two scalarsets\n"
	    "      //               as in array S1 of S2\n"
	    "      if ( ( count_multisetindex<current_size)\n"
	    "           || ( Perm.MTO_class_%s() && count_%s<%d) )\n"
	    "        {\n"
	    "          exists = FALSE;\n"
	    "          split = FALSE;\n"
	    "          for (k=0; k<current_size; k++) // step through class\n"
	    "            if (!(*this)[k]%s.isundefined())\n"
	    "              split = TRUE;\n"
	    "          if (split)\n"
	    "            {\n"
	    "              for (i=0; i<count_multisetindex; i++) // scan through array index priority\n"
	    "                for (j=0; j<count_%s; j++) //scan through element priority\n"
	    "                  {\n"
	    "                    exists = FALSE;\n"
	    "                    for (k=0; k<current_size; k++) // initialize goodset\n"
	    "                      goodset_multisetindex[k] = FALSE;\n"
	    "                    for (k=0; k<%d; k++) // initialize goodset\n"
	    "                      goodset_%s[k] = FALSE;\n"
	    "                    for (k=0; k<current_size; k++) // scan array index\n"
	    "                      // set goodsets\n"
	    "                      if (pos_multisetindex[i][k] \n"
	    "                          && !(*this)[k]%s.isundefined()\n"
	    "                          && pos_%s[j][(*this)[k]%s-%d])\n"
	    "                        {\n"
	    "                          exists = TRUE;\n"
	    "                          goodset_multisetindex[k] = TRUE;\n"
	    "                          goodset_%s[(*this)[k]%s-%d] = TRUE;\n"
	    "                        }\n"
	    "                    if (exists)\n"
	    "                      {\n"
	    "                        // set split for the array index type\n"
	    "                        split=FALSE;\n"
	    "                        for (k=0; k<current_size; k++)\n"
	    "                          if ( pos_multisetindex[i][k] && !goodset_multisetindex[k] )\n"
	    "                            split= TRUE;\n"
	    "                        if (split)\n"
	    "                          {\n"
	    "                            // move following pos entries down 1 step\n"
	    "                            for (z=count_multisetindex; z>i; z--)\n"
	    "                              for (k=0; k<current_size; k++)\n"
	    "                                pos_multisetindex[z][k] = pos_multisetindex[z-1][k];\n"
	    "                            // split pos\n"
	    "                            for (k=0; k<current_size; k++)\n"
	    "                              {\n"
	    "                                if (pos_multisetindex[i][k] && !goodset_multisetindex[k])\n"
	    "                                  pos_multisetindex[i][k] = FALSE;\n"
	    "                                if (pos_multisetindex[i+1][k] && goodset_multisetindex[k])\n"
	    "                                  pos_multisetindex[i+1][k] = FALSE;\n"
	    "                              }\n"
	    "                            count_multisetindex++;\n"
	    "                          }\n"
	    "                        // set split for the element type\n"
	    "                        split=FALSE;\n"
	    "                        for (k=0; k<%d; k++)\n"
	    "                          if ( pos_%s[j][k] && !goodset_%s[k] )\n"
	    "                            split= TRUE;\n"
	    "                        if (split)\n"
	    "                          {\n"
	    "                            // move following pos entries down 1 step\n"
	    "                            for (z=count_%s; z>j; z--)\n"
	    "                              for (k=0; k<%d; k++)\n"
	    "                                pos_%s[z][k] = pos_%s[z-1][k];\n"
	    "                            // split pos\n"
	    "                            for (k=0; k<%d; k++)\n"
	    "                              {\n"
	    "                                if (pos_%s[j][k] && !goodset_%s[k])\n"
	    "                                  pos_%s[j][k] = FALSE;\n"
	    "                                if (pos_%s[j+1][k] && goodset_%s[k])\n"
	    "                                  pos_%s[j+1][k] = FALSE;\n"
	    "                              }\n"
	    "                            count_%s++;\n"
	    "                          }\n"
	    "                      }\n"
	    "                  }\n"
	    "            }\n"
	    "        }\n",
	    name2, name2, size2,
	    var,

	    name2,
	    size2, name2,
	    var,
	    name2, var, left2,
	    name2, var, left2,

	    size2,
	    name2, name2,
	    name2, size2, name2, name2,
	    size2, name2, name2, name2,
	    name2, name2, name2,
	    name2

	    );
}
