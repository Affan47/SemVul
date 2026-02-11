gl_merge_evolution_copy (glMerge       *dst_merge,
                         const glMerge *src_merge)
{
        GList *src_iter, *dst_iter;

        glMergeEvolution *dst_merge_evolution;
        glMergeEvolution *src_merge_evolution;

        gl_debug (DEBUG_MERGE, "BEGIN");

        dst_merge_evolution = GL_MERGE_EVOLUTION (dst_merge);
        src_merge_evolution = GL_MERGE_EVOLUTION (src_merge);

        dst_merge_evolution->priv->query = g_strdup(src_merge_evolution->priv->query);

        dst_merge_evolution->priv->fields = g_list_copy(src_merge_evolution->priv->fields);
        for (src_iter = src_merge_evolution->priv->fields,
                     dst_iter = dst_merge_evolution->priv->fields;
             src_iter != NULL && dst_iter != NULL;
             src_iter = g_list_next(src_iter), dst_iter = g_list_next(dst_iter))
        {
                dst_iter->data = g_new(EContactField, 1);
                if (src_iter->data) {
                        memcpy(dst_iter->data, src_iter->data, sizeof(EContactField));
                }
        }


        gl_debug (DEBUG_MERGE, "END");
}
