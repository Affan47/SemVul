cr_statement_unlink (CRStatement * a_stmt)
{
        CRStatement *result = a_stmt;

        g_return_val_if_fail (result, NULL);


        if (a_stmt->next) {
                g_return_val_if_fail (a_stmt->next->prev == a_stmt, NULL);
        }
        if (a_stmt->prev) {
                g_return_val_if_fail (a_stmt->prev->next == a_stmt, NULL);
        }


        if (a_stmt->next) {
                a_stmt->next->prev = a_stmt->prev;
        }
        if (a_stmt->prev) {
                a_stmt->prev->next = a_stmt->next;
        }

        if (a_stmt->parent_sheet
            && a_stmt->parent_sheet->statements == a_stmt) {
                a_stmt->parent_sheet->statements =
                        a_stmt->parent_sheet->statements->next;
        }

        a_stmt->next = NULL;
        a_stmt->prev = NULL;
        a_stmt->parent_sheet = NULL;

        return result;
}
