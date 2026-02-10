pack_cells(ref_t* href)
{
    ref_t ref = *href--;
    if (ref == ROOT_REF) {
        return;
    }

    if (cell_[ref].is_left_ref_ || cell_[ref].is_right_ref_ ||
        cell_[ref].left_.bitmap_ != cell_[ref].right_.bitmap_) {
        return;
    }

    const bitmap_t bitmap = cell_[ref].left_.bitmap_;

    do {
        ref = *href--;

        if (!cell_[ref].is_left_ref_) {
            if (cell_[ref].left_.bitmap_ != bitmap) {
                break;
            }

        } else if (!cell_[ref].is_right_ref_) {
            if (cell_[ref].right_.bitmap_ != bitmap) {
                break;
            }

        } else {
            break;
        }

    } while (ref != ROOT_REF);

    const ref_t par_ref = href[2];

    if (cell_[ref].is_left_ref_ && cell_[ref].left_.ref_ == par_ref) {
        cell_[ref].is_left_ref_ = false;
        cell_[ref].left_.bitmap_ = bitmap;
    } else {
        cell_[ref].is_right_ref_ = false;
        cell_[ref].right_.bitmap_ = bitmap;
    }

    free_cell(par_ref);
}
