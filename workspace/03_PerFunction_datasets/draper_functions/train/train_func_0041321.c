addComment(const QString& username, const QString& comment)
{

    QString t;

    t += m_log->toHtml();

    QString email = "spillner@kde.org";

    t += "<a href='" + email + "'>" + Qt::escape(username) + "</a>"
         + "<table class='itemBox'>"
         + "<tr>"
         + "<td class='contentsColumn'>"
         + "<table class='contentsHeader' cellspacing='2' cellpadding='0'><tr>"
         + "<td>Comment!</td>"
         + "</tr></table>"
         + "<div class='contentsBody'>"
         + Qt::escape(comment)
         + "</div>"
         + "<div class='contentsFooter'>"
         + "<em>" + Qt::escape(username) + "</em>"
         + "</div>"
         + "</td>"
         + "</tr>"
         + "</table>";

    m_log->setHtml(t);
}
