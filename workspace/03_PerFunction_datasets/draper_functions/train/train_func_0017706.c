about_build_interface(about_t *about)
{

  GtkWidget           *vbox;
  GtkWidget           *label;

  g_assert(about != NULL);
  g_assert(about->apwal != NULL);
  g_assert(about->apwal->about_frame != NULL);


  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
  gtk_box_set_spacing(GTK_BOX(vbox), 4);
  gtk_container_add(GTK_CONTAINER(about->apwal->about_frame), vbox);
  gtk_widget_show(vbox);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label),
"<span size='xx-large'>Apwal</span>\nv" APWAL_VERSION);
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_label_set_selectable(GTK_LABEL(label), TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
  gtk_widget_show(label);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label),
"<span size='large' underline='single'>http://apwal.free.fr</span>");
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_label_set_selectable(GTK_LABEL(label), TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
  gtk_widget_show(label);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label),
"<small>Copyright (C) 2002-2004 Pascal Eberhard\nemail: pascal.ebo@laposte.net\n</small>");
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_label_set_selectable(GTK_LABEL(label), TRUE);
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
  gtk_widget_show(label);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label),
"This program is free software; you can redistribute it and/or " \
"modify it under the terms of the GNU General Public License as " \
"published by the Free Software Foundation; either version 2 of the " \
"License, or (at your option) any later version." \
"\n\n" \
"This program is distributed in the hope that it will be useful, " \
"but WITHOUT ANY WARRANTY; without even the implied warranty of " \
"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU " \
"General Public License for more details." \
"\n\n" \
"You should have received a copy of the GNU General Public " \
"License along with this program; if not, write to the " \
"Free Software Foundation, Inc., 59 Temple Place - Suite 330, " \
"Boston, MA 02111-1307, USA.");
  gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
  gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
  gtk_label_set_selectable(GTK_LABEL(label), TRUE);
  gtk_box_pack_end(GTK_BOX(vbox), label, TRUE, TRUE, 0);
  gtk_widget_show(label);


}
