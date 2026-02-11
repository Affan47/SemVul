VuotaCLista(void)
{
    while (totale_lista_c--) {
        if (c_list[totale_lista_c]) {
            free(c_list[totale_lista_c]);
            c_list[totale_lista_c] = NULL;
        }
    }
}
