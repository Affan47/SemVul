after_reorder(void)
{
    if (previous_image != NULL &&
        current_image->node->prev != previous_image->node) {

        forget_image(&previous_image);
    }

    if (next_image != NULL && current_image->node->next != next_image->node) {
        forget_image(&next_image);
    }

    update_current_image_status(TRUE);
}
