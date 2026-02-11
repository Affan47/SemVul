showadvancedform(void){
  const char *rp;
  int i;
  xmlprintf("<div class=\"form_advanced\">\n");
  xmlprintf("<table summary=\"condition\" class=\"condition\">\n");
  xmlprintf("<tr>\n");
  xmlprintf("<th class=\"ilabel\" abbr=\"phrase\">phrase:</th>\n");
  xmlprintf("<td class=\"ivalue\">\n");
  xmlprintf("<input type=\"text\" name=\"phrase\" value=\"%@\""
            " size=\"64\" id=\"phrase\" class=\"text\" tabindex=\"%d\" accesskey=\"0\" />\n",
            p_phrase, ++g_tabidx);
  xmlprintf("</td>\n");
  xmlprintf("</tr>\n");
  for(i = 0; i < 3; i++){
    xmlprintf("<tr>\n");
    xmlprintf("<th class=\"ilabel\" abbr=\"attribute\">attribute:</th>\n");
    xmlprintf("<td class=\"ivalue\">\n");
    if(!(rp = cblistval(g_attrlist, i, NULL))) rp = "";
    xmlprintf("<input type=\"text\" name=\"attr%d\" value=\"%@\""
              " size=\"64\" id=\"attr%d\" class=\"text\" tabindex=\"%d\" accesskey=\"%d\" />\n",
              i, rp, i, ++g_tabidx, i);
    xmlprintf("</td>\n");
    xmlprintf("</tr>\n");
  }
  xmlprintf("<tr>\n");
  xmlprintf("<th class=\"ilabel\" abbr=\"order\">order:</th>\n");
  xmlprintf("<td class=\"ivalue\">\n");
  xmlprintf("<input type=\"text\" name=\"order\" value=\"%@\""
            " size=\"64\" id=\"order\" class=\"text\" tabindex=\"%d\" accesskey=\"0\" />\n",
            p_order, ++g_tabidx);
  xmlprintf("</td>\n");
  xmlprintf("</tr>\n");
  if(cblistnum(g_genrechecks) > 0){
    xmlprintf("<tr>\n");
    xmlprintf("<th class=\"ilabel\" abbr=\"genre\">genre:</th>\n");
    xmlprintf("<td class=\"ivalue\">\n");
    showgenreform();
    xmlprintf("</td>\n");
    xmlprintf("</tr>\n");
  }
  xmlprintf("<tr>\n");
  xmlprintf("<th class=\"ilabel\" abbr=\"perpage\">per page:</th>\n");
  xmlprintf("<td class=\"ivalue\">\n");
  showperpageform(NULL);
  xmlprintf("</td>\n");
  xmlprintf("</tr>\n");
  xmlprintf("<tr>\n");
  xmlprintf("<th class=\"ilabel\" abbr=\"clip\">clip:</th>\n");
  xmlprintf("<td class=\"ivalue\">\n");
  showclipform(NULL);
  xmlprintf("</td>\n");
  xmlprintf("</tr>\n");
  xmlprintf("<tr>\n");
  xmlprintf("<th class=\"ilabel\" abbr=\"phrase\">action:</th>\n");
  xmlprintf("<td class=\"ivalue\">\n");
  xmlprintf("<input type=\"submit\" value=\"Search\""
            " id=\"search\" class=\"submit\" tabindex=\"%d\" accesskey=\"8\" />\n",
            ++g_tabidx);
  xmlprintf("<input type=\"reset\" value=\"Reset\""
            " id=\"reset\" class=\"reset\" tabindex=\"%d\" accesskey=\"9\" />\n",
            ++g_tabidx);
  xmlprintf("</td>\n");
  xmlprintf("</tr>\n");
  xmlprintf("</table>\n");
  xmlprintf("<span class=\"inputhidden\">\n");
  xmlprintf("<input type=\"hidden\" name=\"navi\" value=\"%d\" id=\"navi\" />\n", p_navi);
  xmlprintf("</span>\n");
  xmlprintf("</div>\n");
}
