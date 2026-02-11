put_common_group(FILE *fp, CommonGroup *group)
{
    List *li;

    fprintf(fp, "CommonGroup: [array_size=%-10dtotal_size=%-10d] ",
            group->array_size, group->total_size);

    for (li = group->region_info_list; li != NULL; li = li->next) {
        RegionInfo *info = (RegionInfo *)li->data;
        fprintf(fp, "%s#%d", info->region->name, info->region->entry);
        if (li->next != NULL)
            fprintf(fp, ",");
    }
    fprintf(fp, "\n");
}
