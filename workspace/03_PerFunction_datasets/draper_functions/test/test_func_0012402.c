fput_hmdf_tree(FILE *fp, Block *head, int depth)
{
    Block *bpt;
    int i;

    for (bpt = head; bpt != NULL; bpt = bpt->next) {
        if (is_parallel_do_loop(bpt))
            continue;

        if (bpt->hmdf != NULL) {
            for (i = 0; i < bpt->hmdf->depth - 1; i++) {
                fprintf(fp, "     ");
            }
            mfprintf(fp,
                     "%B: depth = %d, pc = %d, pe = %d\n",
                     bpt,
                     bpt->hmdf->depth,
                     bpt->hmdf->pc_num,
                     bpt->hmdf->pe_num);

            if (bpt->inner != NULL
                && inner_block_has_hmdf(bpt->inner)) {
                for (i = 0; i < bpt->hmdf->depth - 1; i++) {
                    fprintf(fp, "     ");
                }
                mfprintf(fp, "%B : start\n", bpt);
                fput_hmdf_tree(fp, bpt->inner, bpt->hmdf->depth);
                for (i = 0; i < bpt->hmdf->depth - 1; i++) {
                    fprintf(fp, "     ");
                }
                mfprintf(fp, "%B : end\n", bpt);
            }
            continue;
        }

        if (bpt->inner != NULL
            && inner_block_has_hmdf(bpt->inner)) {
            for (i = 0; i < depth - 1; i++) {
                fprintf(fp, "     ");
            }
            mfprintf(fp, "%B : start\n", bpt);
            fput_hmdf_tree(fp, bpt->inner, depth);
            for (i = 0; i < depth - 1; i++) {
                fprintf(fp, "     ");
            }
            mfprintf(fp, "%B : end\n", bpt);
            continue;
        }

        if (bpt->kind == SB) {
            Module_table *sb = sb_callee(bpt);
            if (sb_has_hmdf(sb)) {
                for (i = 0; i < depth - 1; i++) {
                    fprintf(fp, "     ");
                }
                mfprintf(fp, "%B ( %s ) : start\n", bpt, sb->name);
                fput_hmdf_tree(fp, sb->block_head, depth);
                for (i = 0; i < depth - 1; i++) {
                    fprintf(fp, "     ");
                }
                mfprintf(fp, "%B ( %s ) : end\n", bpt, sb->name);
            }
            continue;
        }
    }
}
