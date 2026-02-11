reorder_citations(char *keys, int scan_aux_code)
{
    char *key, *remaining_keys,*ordered_keys,*a,*b;
    int n,i;
    int dash;
    citekey_type names[100];

    diagnostics(4,"original list <%s> scan aux code=%d",keys,scan_aux_code);


    key = keys;
    remaining_keys = popCommaName(key);
    n=0;
    while (key  && n < 100) {
        char *s = ScanAux(BIBCITE_TOKEN, key, scan_aux_code);
        if (s) {
            int number;
            sscanf(s,"%d",&number);
            safe_free(s);
            names[n].key = key;
            names[n].number = number;
            n++;
        }
        key = remaining_keys;
        remaining_keys = popCommaName(key);
    }


    if (n<=1) {
        ordered_keys = strdup(keys);
        return ordered_keys;
    }


    qsort(names, n, sizeof(citekey_type), CmpFunc);


    ordered_keys=strdup(names[0].key);
    dash = FALSE;

    for (i=1; i<n; i++) {
        if (g_compressed_citations && dash && i!=n-1 && names[i].number+1==names[i+1].number)
            continue;

        a = strdup_together(ordered_keys, ",");

        if (g_compressed_citations && !dash && i!=n-1 && names[i-1].number+2==names[i+1].number) {

            dash = TRUE;
            b = strdup_together(a, BIB_DASH_MARKER);
        } else {

            dash = FALSE;
            b = strdup_together(a, names[i].key);
        }
        safe_free(a);
        safe_free(ordered_keys);
        ordered_keys=b;
    }

    diagnostics(4,"compressed list <%s>",ordered_keys);
    return ordered_keys;
}
