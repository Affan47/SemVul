init_common_tags(gsicc_tag tag_list[],int num_tags, int *last_tag)
{


    int curr_tag, temp_size;

    if (*last_tag < 0)
        curr_tag = 0;
    else
        curr_tag = (*last_tag)+1;

    tag_list[curr_tag].offset = HEADER_SIZE+num_tags*TAG_SIZE + 4;
    tag_list[curr_tag].sig = icSigProfileDescriptionTag;

    temp_size = 2*strlen(desc_name) + 28;

    tag_list[curr_tag].byte_padding = get_padding(temp_size);
    tag_list[curr_tag].size = temp_size + tag_list[curr_tag].byte_padding;

    curr_tag++;

    tag_list[curr_tag].offset = tag_list[curr_tag-1].offset +
                                                    tag_list[curr_tag-1].size;
    tag_list[curr_tag].sig = icSigCopyrightTag;

    temp_size = 2*strlen(copy_right) + 28;
    tag_list[curr_tag].byte_padding = get_padding(temp_size);
    tag_list[curr_tag].size = temp_size + tag_list[curr_tag].byte_padding;
    *last_tag = curr_tag;
}
