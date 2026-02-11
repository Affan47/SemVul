virt_fullname(PT_probematch * ml)
{
    if (gene_flag) {
        const gene_struct *gs = get_gene_struct_by_internal_gene_name(psg.data[ml->name].name);
        return gs ? gs->get_arb_gene_name() : "<cantResolveGeneFullname>";
    }
    else {
        return psg.data[ml->name].fullname ?  psg.data[ml->name].fullname : "<undefinedFullname>";
    }
}
