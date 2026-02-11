GC_push_selected(ptr_t bottom, ptr_t top,
                               GC_bool (*dirty_fn)(struct hblk *))
  {
    struct hblk * h;

    bottom = (ptr_t)(((word) bottom + ALIGNMENT-1) & ~(ALIGNMENT-1));
    top = (ptr_t)(((word) top) & ~(ALIGNMENT-1));
    if (bottom >= top) return;

    h = HBLKPTR(bottom + HBLKSIZE);
    if (top <= (ptr_t) h) {
        if ((*dirty_fn)(h-1)) {
            GC_push_all(bottom, top);
        }
        return;
    }
    if ((*dirty_fn)(h-1)) {
        GC_push_all(bottom, (ptr_t)h);
    }

    while ((ptr_t)(h+1) <= top) {
        if ((*dirty_fn)(h)) {
            if ((word)(GC_mark_stack_top - GC_mark_stack)
                > 3 * GC_mark_stack_size / 4) {

                GC_push_all((ptr_t)h, top);
                return;
            } else {
                GC_push_all((ptr_t)h, (ptr_t)(h+1));
            }
        }
        h++;
    }

    if ((ptr_t)h != top && (*dirty_fn)(h)) {
       GC_push_all((ptr_t)h, top);
    }
    if (GC_mark_stack_top >= GC_mark_stack_limit) {
        ABORT("Unexpected mark stack overflow");
    }
  }
