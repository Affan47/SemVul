reg_addr( const DataType& term, const DataType& reg ) {
    if (STR_DATA != reg.get_type()) return reg;

    NodeRef pterm = find_name_or_addr( di, term );
    return find_name_or_addr( pterm, reg )->get_attr("addr");
}
