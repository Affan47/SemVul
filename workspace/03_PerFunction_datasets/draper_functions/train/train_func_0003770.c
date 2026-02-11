avi_writer_close (AviWriter *self) {
    avi_writer_pop_chunk(self);
    avi_writer_write_index(self);
    avi_writer_pop_chunk(self);


    g_assert(self->chunk_stack == NULL);


    fseek(self->file, self->frame_count_offset, SEEK_SET);
    write_int32(self->file, self->frame_count);
    fseek(self->file, self->length_offset, SEEK_SET);
    write_int32(self->file, self->frame_count * self->frame_rate * RATE_SCALE);

    fclose(self->file);
    g_queue_free(self->index_queue);
}
