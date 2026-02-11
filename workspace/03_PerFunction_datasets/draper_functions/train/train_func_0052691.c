HW_page_hit(int page_table_index, int page_num) {


    if(!(page_tables[page_table_index][0].bits & P_BITMASK)) {
        return ERROR_PAGE_TABLE_NOT_INIT;
    }

    if(!(page_tables[page_table_index][page_num].bits & P_BITMASK)) {
        return ERROR_PAGE_NOT_INIT;
    }

    if(!(page_tables[page_table_index][page_num].bits & PMV_BITMASK)) {
        return ERROR_HARDWARE_NOT_IN_PHY_MEM;
    }
    byte addr = page_tables[page_table_index][page_num].phy_addr;
    global_LRU_counter++;
    checkoverflow();
    phy_mem[addr].LRU = global_LRU_counter;
    return ERROR_SUCCESS;
}
