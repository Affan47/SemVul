read_header(int fd, COW_Header & header)
{
    int res;

    if((res = ::read(fd, &header, sizeof(COW_Header))) < 0)
      return res;

    DTOH32_HEADER(header_version);
    DTOH32_HEADER(flags);
    DTOH32_HEADER(total_sectors);
    DTOH32_HEADER(tlb_size_sectors);
    DTOH32_HEADER(flb_offset_sectors);
    DTOH32_HEADER(flb_count);
    DTOH32_HEADER(next_sector_to_allocate);
    DTOH32_HEADER(cylinders);
    DTOH32_HEADER(heads);
    DTOH32_HEADER(sectors);
    DTOH32_HEADER(last_modified_time);
    DTOH32_HEADER(last_modified_time_save);
    DTOH32_HEADER(chain_id);
    DTOH32_HEADER(number_of_chains);
    DTOH32_HEADER(cylinders_in_disk);
    DTOH32_HEADER(heads_in_disk);
    DTOH32_HEADER(sectors_in_disk);
    DTOH32_HEADER(total_sectors_in_disk);
    DTOH32_HEADER(vmware_version);

    return res;
}
