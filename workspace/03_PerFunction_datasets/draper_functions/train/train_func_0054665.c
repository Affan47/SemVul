update_from_option (GSTPPipelineEditor * editor,
    GSTPPipelineDescription * pipeline_desc)
{


  editor->cur_pipeline_index = pipeline_desc->index;


  update_device_menu(editor, pipeline_desc);

  if (pipeline_desc->is_custom == FALSE) {
    gchar *pipeline = gst_pipeline_string_from_desc(pipeline_desc);
    if (pipeline)
      gtk_entry_set_text (editor->entry, pipeline);
    gtk_widget_set_sensitive (GTK_WIDGET (editor->entry), FALSE);


    gst_properties_gconf_set_string (editor->gconf_key, pipeline);
  } else {
    gtk_widget_set_sensitive (GTK_WIDGET (editor->entry), TRUE);
  }
}
