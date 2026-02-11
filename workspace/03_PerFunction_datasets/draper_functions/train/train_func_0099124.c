show_top5_leaders_size ()
{
    int i = 0;
    for (; i <= last_index; i++) {
        int leader_size = leaders[i];
        if (leader_size > 0) {
            if (leader_size > top5_leaders_size[0]) {
                insert_top5 (0, leader_size);
            } else if (leader_size > top5_leaders_size[1]) {
                insert_top5 (1, leader_size);
            } else if (leader_size > top5_leaders_size[2]) {
                insert_top5 (2, leader_size);
            } else if (leader_size > top5_leaders_size[3]) {
                insert_top5 (3, leader_size);
            } else if (leader_size > top5_leaders_size[4]) {
                insert_top5 (4, leader_size);
            }
        }
    }

    for (i=0; i < 4; i++) {
        printf("%i,", top5_leaders_size[i]);
    }
    printf("%i\n", top5_leaders_size[4]);
}
